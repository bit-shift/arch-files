" Plugin set up - using Vundle
set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'kadekillary/Turtles'
Plugin 'flazz/vim-colorschemes'
Plugin 'joshdick/onedark.vim'
Plugin 'itchyny/lightline.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'lervag/vimtex'
Plugin 'tpope/vim-fugitive'
call vundle#end()
filetype plugin indent on

" YouCompleteMe fallback path
let g:ycm_global_ycm_extra_conf = '/home/keegan/.ycm_extra_conf.py'
let g:ycm_confirm_extra_conf = 0

" vimtex settings
let g:tex_flavor = 'latex'
let g:vimtex_view_method = 'zathura'

" vimtex youcompleteme
if !exists('g:ycm_semantic_triggers')
	let g:ycm_semantic_triggers = {}
endif
let g:ycm_semantic_triggers.tex = g:vimtex#re#youcompleteme

" vimura
function! Synctex()
	" remove 'silent' for debugging
	execute "silent !zathura --synctex-forward " . line('.') . ":" . col('.') . ":" . bufname('%') . " " . g:syncpdf
endfunction
map <C-CR> :call Synctex()<CR>

" Auto-complete
set wildmode=longest,list,full

" Split navigation shortcuts
map <C-h> <C-w>h
map <C-j> <C-w>j
map <C-k> <C-w>k
map <C-l> <C-w>l

" Set the colour scheme to use the 16 colours in .Xresources
" set t_Co=16

" Set the colour scheme 
colorscheme onedark
let g:lightline = {
	\ 'colorscheme': 'onedark',
	\ 'active': {
	\ 	'left': [ [ 'mode', 'paste' ], 
	\			[ 'gitbranch', 'readonly', 'filename', 'modified' ] ]
	\ },
	\ 'component_function': {
	\	'gitbranch': 'fugitive#head'
	\ },
	\ }

" Load the status bar
set laststatus=2

" Configuration
syntax on
set encoding=utf-8
set number relativenumber
set tabstop=4
set shiftwidth=4
set showmatch
set noshowmode
set showcmd
set mouse=a
set matchpairs+=<:>

" Searching
set hlsearch
set incsearch
set smartcase
