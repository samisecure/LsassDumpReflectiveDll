### this project make a reflective DLL for use in post exploit state to dump lsass memory without touch hard disk. 
this proejct Create a Reflective DLL Injector and a Reflective DLL for dump lsass memory without touch hard disk.

for test DLL by injector you can run :
#.\inject.x64.exe  <PID of Victim Process to inject> <Path to reflective dll: .\LsassDumpReflectiveDLL.dll>
  
for use in metasploit framework: locate LsassDumpReflectiveDLL.dll to your kali,  make a meterpreter sessionto victim system  and use  Metasploit–Reflective DLL Injection Module. 

Refrences:
  
  https://github.com/stephenfewer/ReflectiveDLLInjection
  https://quantumcored.com/index.php/2021/03/26/beginners-guide-to-reflective-dll-injection/
  
