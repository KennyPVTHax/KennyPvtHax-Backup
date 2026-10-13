import importlib.util,io,json,os,subprocess,tempfile,struct,zipfile
from pathlib import Path
spec=importlib.util.spec_from_file_location('release','tools/loader_release.py');r=importlib.util.module_from_spec(spec);spec.loader.exec_module(r)
def run(*args):return subprocess.check_output(['git',*map(str,args)],stderr=subprocess.DEVNULL).decode().strip()
def binary():
    b=bytearray(128);b[:7]=b'\x7fELF'+bytes((2,1,1));struct.pack_into('<HH',b,16,3,183);return bytes(b)
policy={'verified':True,'scheme':'decimal-step','step':'0.1','evidence':'Unit test only: numeric decimal comparison'}
contract=r.load('tools/loader_contract.json');assert not contract['version_policy']['verified'];assert not contract['initial_device_milestone_approved']
for version in ['nan','0.2.0','2','-0.2']:
 rejected=False
 try:r.next_version(version,policy)
 except AssertionError:rejected=True
 assert rejected,'accepted bad version'
assert r.next_version('0.2',policy)=='0.3';assert r.next_version('0.9',policy)=='1.0'
manifest={'app_version':'1.0','isEnableLog':False,'games':[{'package':'other','status':False},{'package':'com.pubg.imobile','drm':'x','drm_name':'old.zip','drm_verion':'0.2','status':True,'deskripsi':'unchanged'}]}
fields=dict(zip(r.KEYS,['url','new.zip','0.3']));updated=r.edit_manifest(manifest,fields);assert updated['games'][0]==manifest['games'][0] and updated['app_version']=='1.0';assert updated['games'][1]['deskripsi']=='unchanged' and manifest['games'][1]['drm']=='x'
with tempfile.TemporaryDirectory() as temp:
 root=Path(temp);so=root/'source.so';so.write_bytes(binary());bundle=root/'bundle';report=r.package(so,bundle,'a'*40,'unit',contract);assert r.archive((bundle/report['zip_name']).read_bytes(),contract)==so.read_bytes()
 try:r.package(so,bundle,'a'*40,'unit',contract)
 except AssertionError:pass
 else:raise AssertionError('overwrote archive')
 # Real local Git remote: publication commits ZIP+manifest together and rollback
 # changes only manifest. No real GitHub destination is touched by tests.
 remote=root/'remote.git';run('init','--bare',remote);seed=root/'seed';run('clone',remote,seed);run('-C',seed,'checkout','-b','main');run('-C',seed,'config','user.name','Fixture');run('-C',seed,'config','user.email','fixture@example.invalid')
 original=json.loads(json.dumps(manifest));g=r.game(original);g.update(drm='https://raw.githubusercontent.com/'+r.DEST+'/main/test2.zip',drm_name='test2.zip')
 with zipfile.ZipFile(seed/'test2.zip','w') as z:z.writestr('libloader.so',binary())
 (seed/'kenny.json').write_text(json.dumps(original));run('-C',seed,'add','.');run('-C',seed,'commit','-m','original');run('-C',seed,'push','origin','main');old=run('-C',seed,'rev-parse','HEAD')
 actual_git=r.git
 def local_git(path,*args,**kwargs):
  if args[0]=='clone':args=(*args[:4],str(remote),args[-1])
  return actual_git(path,*args,**kwargs)
 r.git=local_git;r.current_source=lambda commit:None
 def local_raw(url,timeout):
  parts=url.split('/');commit=parts[-2];name=parts[-1];return io.BytesIO(subprocess.check_output(['git','--git-dir',str(remote),'show',commit+':'+name]))
 r.urllib.request.urlopen=local_raw
 os.environ.update(GITHUB_REPOSITORY=r.SOURCE,GITHUB_REF='refs/heads/release/android',GITHUB_EVENT_NAME='workflow_dispatch',GITHUB_SHA='a'*40,ANILXKENNY_PUBLISH_TOKEN='unit-test-only')
 contract['version_policy']=policy;contract['initial_device_milestone_approved']=True
 published=r.publish(bundle,contract);assert published['manifest_version']=='0.3'
 changes=run('--git-dir',remote,'diff-tree','--no-commit-id','--name-only','-r',published['destination_commit']).splitlines();assert set(changes)=={'kenny.json',report['zip_name']}
 assert r.publish(bundle,contract)['result']=='already-published'
 rollback=r.publish(bundle,contract,old);assert rollback['manifest_version']=='0.2';assert run('--git-dir',remote,'show','main:kenny.json')==json.dumps(original,indent=4)
 assert run('--git-dir',remote,'ls-tree','--name-only','main',report['zip_name'])==report['zip_name']
 os.environ['GITHUB_REF']='refs/heads/main'
 try:r.publish(bundle,contract)
 except AssertionError:pass
 else:raise AssertionError('main published')
print('PASS package bytes/CRC/name/immutability; manifest package lookup and preservation; unverified version gate; real local atomic Git publication, idempotency and rollback archive retention; main denied. Version arithmetic is a test-only candidate, not confirmed loader behavior.')
