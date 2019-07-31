# Important note
Installing OpenSSL is necessary for the requests to Discogs to succeed.
1. Install OpenSSL from here: https://slproweb.com/products/Win32OpenSSL.html.
Choose the 32-bit or 64-bit version according to the installed compiler.
Make sure to install a 1.0 and not 1.1 version.
2. For my personal case, I installed https://slproweb.com/download/Win64OpenSSL-1_0_2s.exe in C:\Program Files\OpenSSL-1.0-Win64.
Then I copied libeay32.dll, libssl32.dll and ssleay32.dll in the directory where compiled binaries are located.
It magically worked.
It needs to be refined to make it smoother for the user (and developer).
3. From Qt 5.13.0, it seems that Qt supports OpenSSL from higher version. Therefore you can install a newer version of OpenSSL, such as https://slproweb.com/download/Win64OpenSSL-1_1_1c.exe. Then you can copy libcrypto-1_1-x64.dll and libssl-1_1-x64.dll to the directory where compiled binaries are located.
