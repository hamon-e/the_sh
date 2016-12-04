
complete -c abook -s h -d 'Show usage'
complete -c abook -s C -l config -d 'Use an alternative configuration file' -r
complete -c abook      -l datafile -d 'Use an alternative addressbook file' -r
complete -c abook      -l mutt-query -d 'Make a query for mutt' -x
complete -c abook      -l add-email  -d 'Read email message from stdin and add the sender'
complete -c abook      -l add-email-quiet -d 'Same as --add-email. Without confirmation'
complete -c abook      -l convert  -d 'Convert address book files'
complete -c abook      -l formats   -d 'Print available formats'
