
$cmd_name = "./tools/Astyle/bin/AStyle.exe"
$cmd_args = "--style=google"

start-process -FilePath $cmd_name -ArgumentList "$cmd_args './Test Tools/*.cpp'"
start-process -FilePath $cmd_name -ArgumentList "$cmd_args './Test Tools/*.h'"
start-process -FilePath $cmd_name -ArgumentList "$cmd_args './Test Tools/*.hpp'"