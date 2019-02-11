#!/bin/bash

export PATH="$PATH:$HOME:$HOME/.vim/:$HOME/.local/bin/:$HOME/.scripts/i3blocks/:$HOME/.scripts/tools/"
export EDITOR="vim"
export TERMINAL="urxvt"
export BROWSER="chromium"
export READER="zathura"
export FILE="ranger"
export GPG_TTY=$(tty)

#export MAILCAPS="~/.config/rtv/mailcap"

[ -f ~/.bashrc ] && source "$HOME/.bashrc"

[[ "$(tty)" =~ ^/dev/tty[1-5]$ ]] && startx

sudo -n loadkeys ~/.scripts/tools/escswap &>/dev/null 
