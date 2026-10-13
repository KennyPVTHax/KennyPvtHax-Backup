#!/usr/bin/env python3
"""Bounded loader packaging and atomic Git publication. No native logic changes."""
import argparse, base64, decimal, hashlib, json, os, re, shutil, struct, subprocess, tempfile, urllib.request, urllib.error, zipfile
from pathlib import Path
SOURCE='KennyPVTHax/KennyPvtHax-Backup'; DEST='KennyPVTHax/Anilxkenny'; BRANCH='main'; KEYS=('drm','drm_name','drm_verion')
def digest(data):return hashlib.sha256(data).hexdigest()
def load(path):return json.loads(Path(path).read_text())
def game(data):
    assert isinstance(data,dict) and isinstance(data.get('games'),list),'Invalid manifest'
    matches=[g for g in data['games'] if isinstance(g,dict) and g.get('package')=='com.pubg.imobile']
    assert len(matches)==1,'Expected exactly one target game'
    assert all(isinstance(matches[0].get(k),str) for k in KEYS),'Missing string manifest fields'
    return matches[0]
def elf(data):
    assert len(data)>=64 and data[:4]==b'\x7fELF' and data[4:7]==bytes((2,1,1)),'Not little-endian ELF64'
    assert struct.unpack_from('<HH',data,16)==(3,183),'Not AArch64 shared ELF'
def archive(data,contract):
    with zipfile.ZipFile(__import__('io').BytesIO(data)) as z:
        assert z.namelist()==contract['entries'] and len(z.infolist())==1,'Unexpected loader package entries'
        i=z.infolist()[0];assert not i.is_dir() and not i.flag_bits&1 and 0<i.file_size<100*1024*1024
        assert z.testzip() is None,'ZIP CRC failed'
        b=z.read(i.filename);elf(b);return b

def package(binary,out,commit,run,contract):
    assert re.fullmatch('[0-9a-f]{40}',commit);assert contract['entries']==['libloader.so']
    data=Path(binary).read_bytes();elf(data);out=Path(out);out.mkdir(parents=True,exist_ok=True)
    name=f'kph-{commit}-arm64.zip';target=out/name
    assert not target.exists(),'Immutable archive already exists'
    with zipfile.ZipFile(target,'x',compression=zipfile.ZIP_DEFLATED,compresslevel=9) as z:
        info=zipfile.ZipInfo('libloader.so',(2020,1,1,0,0,0));info.compress_type=zipfile.ZIP_DEFLATED;info.external_attr=0o100644<<16
        z.writestr(info,data)
    raw=target.read_bytes();assert archive(raw,contract)==data
    report={'source_commit':commit,'source_run':run,'ndk':'25.2.9519653','library_sha256':digest(data),'internal_library':'libloader.so','zip_name':name,'zip_sha256':digest(raw),'zip_bytes':len(raw)}
    (out/'release.json').write_text(json.dumps(report,indent=2)+'\n');return report

def next_version(current,policy):
    assert policy.get('verified') is True and policy.get('scheme')=='decimal-step','Version comparison unverified'
    assert isinstance(policy.get('evidence'),str) and len(policy['evidence'])>10
    assert re.fullmatch(r'\d+\.\d+',current) and isinstance(policy.get('step'),str),'Invalid decimal version policy'
    step=decimal.Decimal(policy['step']);old=decimal.Decimal(current)
    assert step.is_finite() and step>0;value=old+step;assert value>old
    s=format(value,'f');return s if '.' in s else s+'.0'
def edit_manifest(data,fields):
    result=json.loads(json.dumps(data));target=game(result)
    assert set(fields)==set(KEYS) and all(isinstance(v,str) for v in fields.values())
    target.update(fields);game(result);return result

def preflight(contract):
    assert os.environ.get('GITHUB_REPOSITORY')==SOURCE and os.environ.get('GITHUB_REF')=='refs/heads/release/android','Only trusted release/android may publish'
    assert os.environ.get('GITHUB_EVENT_NAME') in ('push','workflow_dispatch'),'Untrusted event'
    assert contract['destination']==DEST and contract['branch']==BRANCH and contract['entries']==['libloader.so']
    assert contract.get('initial_device_milestone_approved') is True,'Recovery Stage 1 device approval is pending'
    next_version('0.2',contract['version_policy'])
    assert api(f'repos/{SOURCE}/branches/release/android').get('protected') is True,'release/android is not protected'
def api(path):
    req=urllib.request.Request('https://api.github.com/'+path,headers={'Accept':'application/vnd.github+json','User-Agent':'KennyPvtHax-release'})
    with urllib.request.urlopen(req,timeout=30) as r:return json.load(r)
def current_source(commit):
    assert api(f'repos/{SOURCE}/git/ref/heads/release/android')['object']['sha']==commit,'Stale source run; release branch has advanced'
def git(root,*args,env=None,check=True):
    p=subprocess.run(['git','-C',str(root),*args],env=env,stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True,timeout=120)
    if check and p.returncode:raise RuntimeError('Git operation failed: '+args[0]+' (credentials/output suppressed)')
    return p

def publish(bundle,contract,rollback=None):
    preflight(contract);commit=os.environ['GITHUB_SHA'];assert re.fullmatch('[0-9a-f]{40}',commit)
    token=os.environ.get('ANILXKENNY_PUBLISH_TOKEN');assert token,'ANILXKENNY_PUBLISH_TOKEN is not configured'
    report=load(Path(bundle)/'release.json') if not rollback else None
    if report:
        assert report['source_commit']==commit
        raw=(Path(bundle)/report['zip_name']).read_bytes();assert digest(raw)==report['zip_sha256'];assert digest(archive(raw,contract))==report['library_sha256']
    with tempfile.TemporaryDirectory(prefix='kph-publish-') as tmp:
        tmp=Path(tmp);repo=tmp/'destination';ask=tmp/'askpass.py'
        ask.write_text('#!/usr/bin/env python3\nimport os,sys\nprint("x-access-token" if "username" in sys.argv[1].lower() else os.environ["ANILXKENNY_PUBLISH_TOKEN"])\n');ask.chmod(0o700)
        env=dict(os.environ,GIT_ASKPASS=str(ask),GIT_TERMINAL_PROMPT='0',GIT_CONFIG_COUNT='1',GIT_CONFIG_KEY_0='credential.helper',GIT_CONFIG_VALUE_0='');env.pop('GITHUB_TOKEN',None);env.pop('GH_TOKEN',None)
        # No token in URL, Git configuration or command-line arguments.
        git(tmp,'clone','--branch',BRANCH,'--single-branch','https://github.com/'+DEST+'.git',str(repo),env=env)
        git(repo,'config','user.name','KennyPvtHax release');git(repo,'config','user.email','release@users.noreply.github.com')
        for attempt in range(5):
            current_source(commit)
            git(repo,'fetch','origin',BRANCH,env=env);git(repo,'reset','--hard','origin/'+BRANCH)
            before=load(repo/'kenny.json');target=game(before)
            if rollback:
                assert re.fullmatch('[0-9a-f]{40}',rollback),'Full previous destination commit required'
                prior=json.loads(git(repo,'show',rollback+':kenny.json').stdout);fields={k:game(prior)[k] for k in KEYS}
                name=fields['drm_name'];assert re.fullmatch(r'[A-Za-z0-9._-]+\.zip',name)
                old=git(repo,'rev-parse',rollback+':'+name).stdout.strip();now=git(repo,'rev-parse','HEAD:'+name).stdout.strip();assert old==now,'Historical archive missing/changed'
                archive((repo/name).read_bytes(),contract)
                assert fields['drm']=='https://raw.githubusercontent.com/'+DEST+'/'+BRANCH+'/'+name
                if all(target[k]==fields[k] for k in KEYS):return {'result':'already-rolled-back','destination_commit':git(repo,'rev-parse','HEAD').stdout.strip()}
            else:
                name=report['zip_name'];path=repo/name
                if path.exists():
                    existing=path.read_bytes();installed=archive(existing,contract)
                    if target['drm_name']==name:
                        assert target['drm']=='https://raw.githubusercontent.com/'+DEST+'/'+BRANCH+'/'+name
                        origin=git(repo,'log','--diff-filter=A','--format=%s','--',name).stdout
                        assert ('Publish '+commit+' from source run ') in origin,'Unverified archive filename collision'
                        # Original code uses compilation timestamps: rerunning the
                        # same source may rebuild different bytes. Never replace
                        # the active immutable release; report its actual hashes.
                        return dict(report,result='already-published',destination_commit=git(repo,'rev-parse','HEAD').stdout.strip(),manifest_version=target['drm_verion'],raw_url=target['drm'],rebuilt_library_sha256=report['library_sha256'],library_sha256=digest(installed),zip_sha256=digest(existing),zip_bytes=len(existing))
                    raise RuntimeError('Release archive already exists; refuse automatic replay after rollback')
                path.write_bytes(raw)
                fields={'drm':'https://raw.githubusercontent.com/'+DEST+'/'+BRANCH+'/'+name,'drm_name':name,'drm_verion':next_version(target['drm_verion'],contract['version_policy'])}
            updated=edit_manifest(before,fields);(repo/'kenny.json').write_text(json.dumps(updated,ensure_ascii=False,indent=4)+'\n')
            git(repo,'add','--','kenny.json',*([] if rollback else [name]))
            changed=git(repo,'diff','--cached','--name-only').stdout.splitlines();assert set(changed)==({'kenny.json'} if rollback else {'kenny.json',name})
            git(repo,'commit','-m',('Rollback loader to '+rollback) if rollback else 'Publish '+commit+' from source run '+report['source_run'])
            dest_commit=git(repo,'rev-parse','HEAD').stdout.strip()
            current_source(commit) # Last possible branch-head check before atomic fast-forward push.
            if git(repo,'push','origin','HEAD:'+BRANCH,env=env,check=False).returncode:continue
            git(repo,'fetch','origin',BRANCH,env=env)
            assert git(repo,'merge-base','--is-ancestor',dest_commit,'origin/'+BRANCH,check=False).returncode==0
            published=json.loads(git(repo,'show',dest_commit+':kenny.json').stdout);assert all(game(published)[k]==fields[k] for k in KEYS)
            # Fetch exact committed bytes, not a possibly stale mutable raw URL.
            with urllib.request.urlopen('https://raw.githubusercontent.com/'+DEST+'/'+dest_commit+'/'+name,timeout=30) as r:remote=r.read()
            assert archive(remote,contract)==archive((repo/name).read_bytes(),contract)
            if not rollback:assert digest(remote)==report['zip_sha256']
            return dict(report or {},result='published' if not rollback else 'rolled-back',destination_commit=dest_commit,manifest_version=fields['drm_verion'],raw_url=fields['drm'],zip_name=name)
        raise RuntimeError('Destination contention after five bounded retries; no force push')

def main():
    p=argparse.ArgumentParser();p.add_argument('mode',choices=['package','publish','preflight','rollback']);p.add_argument('--contract',default='tools/loader_contract.json');p.add_argument('--binary',default='libs/arm64-v8a/libAnoy.so');p.add_argument('--bundle',default='deployment');p.add_argument('--commit',default=os.environ.get('GITHUB_SHA'));p.add_argument('--run',default=os.environ.get('GITHUB_RUN_ID','local'));p.add_argument('--previous-commit');a=p.parse_args();contract=load(a.contract)
    if a.mode=='preflight':preflight(contract);print('Production compatibility/device gates passed');return
    if a.mode=='package':report=package(a.binary,a.bundle,a.commit,a.run,contract)
    else:report=publish(a.bundle,contract,a.previous_commit if a.mode=='rollback' else None)
    print(json.dumps(report,indent=2))
    if a.mode in ('publish','rollback'):
        with open(os.environ.get('GITHUB_STEP_SUMMARY','/dev/null'),'a') as f:f.write('```json\n'+json.dumps(report,indent=2)+'\n```\n')
if __name__=='__main__':main()
