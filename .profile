#!/bin/bash

export PATH="$PATH:$HOME:$HOME/cs3231/tools/bin/:$HOME/.vim/:$HOME/.local/bin/:$HOME/.scripts/i3blocks/:$HOME/.scripts/tools/:$HOME/Programming/Python/"
export EDITOR="vim"
export TERMINAL="urxvt"
export BROWSER="chromium"
export READER="zathura"
export FILE="ranger"
export GPG_TTY=$(tty)

#export MAILCAPS="~/.config/rtv/mailcap"

[ -f ~/.bashrc ] && source "$HOME/.bashrc"

# Switch tty with Ctrl+Alt+F# -- 1-5 is i3, after 5 is just console
[[ "$(tty)" =~ ^/dev/tty[1-5]$ ]] && startx

sudo -n loadkeys ~/.scripts/tools/escswap &>/dev/null 
