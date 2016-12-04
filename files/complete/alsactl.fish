complete -c alsactl -s h -l help --description 'Show available flags and commands' -f
complete -c alsactl -s d -l debug --description 'Make output a bit more verbose' -f
complete -c alsactl -s v -l version --description 'Print alsactl version number' -f
complete -c alsactl -s f -l file --description 'Select the configuration file to use'
complete -c alsactl -s l -l lock --description 'Use a lock file'
complete -c alsactl -s L -l no-lock --description 'Do not use a lock file'
complete -c alsactl -s O -l lock-state-file --description 'Select the state lock file path'
complete -c alsactl -s r -l runstate --description 'Save restore and init state to this file'
complete -c alsactl -s R -l remove --description 'Remove runstate file at first'
complete -c alsactl -s E -l env --description 'Set environment variable'
complete -c alsactl -s i -l initfile --description 'The configuration file for init'
complete -c alsactl -s p -l period --description 'The store period in seconds for the daemon command' -f
complete -c alsactl -s e -l pid-file --description 'The PID file to use'
complete -c alsactl -s b -l background --description 'Run the task in background'
complete -c alsactl -s s -l syslog --description 'Use syslog for messages'
complete -c alsactl -s n -l nice --description 'Set the process priority (see \'man nice\')' -a "(seq -20 19)"
complete -c alsactl -s c -l sched-idle --description 'Set the process scheduling policy to idle (SCHED_IDLE)'
