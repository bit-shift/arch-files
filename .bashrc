PS1="\[\033[30;1m\]\[\016\]\[\017\][\[\033[00m\]\u\[\033[34;1m\]@\[\033[00m\]\h\[\033[30;1m\]]-[\[\033[34;1m\]\$(gitprompt)\[\033[30;1m\]]-[\[\[\033[32;1m\]\w\[\033[30;1m\]]-[\[\033[00m\]\$(/bin/ls -Al1 | grep -v '^total' | /usr/bin/wc -l | /bin/sed 's: ::g') items, \$(/bin/ls -lah | /bin/grep -m 1 total | /bin/sed 's/total //')b\[\033[30;1m\]]\n---\[\033[34;1m\]$ \[\033[00m\]"

alias ls="ls -Al | grep -v '^total'"
