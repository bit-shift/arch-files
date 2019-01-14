#!/bin/bash

export PATH="$PATH:$HOME:$HOME/.vim/:$HOME/.local/bin/:$HOME/.scripts/i3blocks/"
export EDITOR="vim"
export TERMINAL="urxvt"
export BROWSER="chromium"

[ -f ~/.bashrc ] && source "$HOME/.bashrc"

[ "$(tty)" = "/dev/tty1" ] && ! pgrep -x i3 >/dev/null && exec startx
