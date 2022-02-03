### this project make a reflective DLL to use in post exploiting state to dump lsass memory without touch hard disk. 
this proejct Create a Reflective DLL Injector and a Reflective DLL for dump lsass memory without touch hard disk.

for test DLL by injector you can run :
#.\inject.x64.exe  <PID of Victim Process to inject> <Path to reflective dll: .\LsassDumpReflectiveDLL.dll>
  lsass.dmp file will save to c:/windows/temp folder.
  
for use in metasploit framework: locate LsassDumpReflectiveDLL.dll to your kali,  make a meterpreter session to victim system  and use  Metasploit–Reflective DLL Injection Module. 

Refrences:
  
  https://github.com/stephenfewer/ReflectiveDLLInjection
  https://pentestlab.blog/2017/04/04/dll-injection/
  https://quantumcored.com/index.php/2021/03/26/beginners-guide-to-reflective-dll-injection/
  
