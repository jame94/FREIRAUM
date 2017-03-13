@ECHO OFF
SET LOCAL="..\..\Software\Assets\FatAssets"
SET REMOTE="\\zeno\endo\users\lemke\Asset Sync Test"

:CHOICE
ECHO Do you want to sync your local assets to the server (PUSH) or sync the remote assets to your local machine (PULL)?
ECHO Please enter PUSH or PULL:
SET /P INPUT=
IF /I "%INPUT%"=="PUSH" GOTO :PUSH
IF /I "%INPUT%"=="PULL" GOTO :PULL

ECHO Unable to make sense of your input.
GOTO :CHOICE

:PUSH
ECHO Just double-checking. Do you REALLY want to?
ECHO Press any key to continue.
PAUSE > NUL
ROBOCOPY %LOCAL% %REMOTE% /MIR
GOTO :END

:PULL
ECHO Just double-checking. Do you REALLY want to?
ECHO Press any key to continue.
PAUSE > NUL
ROBOCOPY %REMOTE% %LOCAL% /MIR
GOTO :END

:END
ECHO Press any key to close the window.
PAUSE > NUL
