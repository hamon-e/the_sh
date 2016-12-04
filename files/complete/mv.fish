complete -c mv -s b -l backup --description "Make backup of each existing destination file"
complete -c mv -s f -l force --description "Do not prompt before overwriting"
complete -c mv -s i -l interactive --description "Prompt before overwrite"
complete -c mv -l reply -x -a "yes no query" --description "Answer for overwrite questions"
complete -c mv -l strip-trailing-slashes --description "Remove trailing slashes from source"
complete -c mv -s S -l suffix -r --description "Backup suffix"
complete -c mv -s u -l update --description "Do not overwrite newer files"
complete -c mv -s v -l verbose --description "Verbose mode"
complete -c mv -l help --description "Display help and exit"
complete -c mv -l version --description "Display version and exit"