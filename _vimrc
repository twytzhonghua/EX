" history存储长度。  
set history=1000 

"支持windows汉字
let &termencoding=&encoding
set fileencodings=utf-8,gb18030,gbk,gb2312,big5


"启动自动补全  
filetype plugin indent on 
 
" 非兼容vi模式。去掉讨厌的有关vi一致性模式，避免以前版本的一些bug和局限  
set nocompatible        
set autoread          " 文件修改之后自动载入。  
" set shortmess=atI       " 启动的时候不显示那个援助索马里儿童的提示

"粘贴时保持格式  
set paste  
" 则点击光标不会换,用于复制  
set mouse-=a           " 在所有的模式下面打开鼠标。  
set selection=exclusive    
set selectmode=mouse,key  

"显示行号：  
set number  
set nowrap                    " 取消换行。  

"为方便复制，用<F2>开启/关闭行号显示:  
"nnoremap <F2> :set nonumber!<CR>:set foldcolumn=0<CR> 
"括号配对情况  
set showmatch  
" How many tenths of a second to blink when matching brackets  
set mat=2  

"设置文内智能搜索提示  
" 高亮search命中的文本。  
set hlsearch            
" 搜索时忽略大小写  
set ignorecase  
" 随着键入即时搜索  
set incsearch  
" 有一个或以上大写字母时仍大小写敏感  
set smartcase  


set tabstop=4                "设置Tab键的宽度        [等同的空格个数]  
set shiftwidth=4 
" 按退格键时可以一次删掉 4 个空格  
set softtabstop=4  


"显示当前的行号列号：  
set ruler  
"在状态栏显示正在输入的命令  
set showcmd  
  

"Set 7 lines to the cursor - when moving vertically using j/k 上下滚动,始终在中间  
set so=7  


  
syntax enable  
syntax on 

"经典配色方案 
colorscheme desert 


"vimrc文件修改之后自动加载
"autocmd! bufwritepost .vimrc source % 

"自动补全配置  
autocmd FileType python set omnifunc=pythoncomplete#Complete 
set backspace=indent,eol,start

set showmatch  
set mat=2  


"--ctags setting--
" 按下F5重新生成tag文件，并更新taglist
map <F5> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR><CR> :TlistUpdate<CR>
imap <F5> <ESC>:!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR><CR> :TlistUpdate<CR>
set tags=tags
set tags+=./tags "add current directory's generated tags file
set tags+=$MAG/tags "add new tags file(刚刚生成tags的路径，在ctags -R 生成tags文件后，不要将tags移动到别的目录，否则ctrl+］时，会提示找不到源码文件)
"set tags+=~/Desktop/linux-2.6.38.2/tags

"-- WinManager setting --
let g:winManagerWindowLayout='FileExplorer|TagList' " 设置我们要管理的插件
"let g:persistentBehaviour=0 "如果所有编辑文件都关闭了，退出vim
"nmap wm :WMToggle<cr>

" -- MiniBufferExplorer -- 
let g:miniBufExplMapWindowNavVim = 1 " 按下Ctrl+h/j/k/l，可以切换到当前窗口的上下左右窗口
let g:miniBufExplMapWindowNavArrows = 1 " 按下Ctrl+箭头，可以切换到当前窗口的上下左右窗口
let g:miniBufExplMapCTabSwitchBufs = 1 " 启用以下两个功能：Ctrl+tab移到下一个buffer并在当前窗口打开；Ctrl+Shift+tab移到上一个buffer并在当前窗口打开；ubuntu好像不支持
"let g:miniBufExplMapCTabSwitchWindows = 1 "启用以下两个功能：Ctrl+tab移到下一个窗口；Ctrl+Shift+tab移到上一个窗口；ubuntu好像不支持
let g:miniBufExplModSelTarget = 1 " 不要在不可编辑内容的窗口（如TagList窗口）中打开选中的buffer

"<F1> 显示minibuffer
map <F1> :WMToggle<CR><CR>
imap <F1> <ESC>:WMToggle<CR><CR>


"<F4> 鼠标可视模式
map <F4> :set mouse=v<CR><CR>
map <F3> :set mouse=a<CR><CR>

imap <F4> <ESC>:set mouse=v<CR><CR>
imap <F3> <ESC>:set mouse=a<CR><CR>

"在vim配置文件/home/user/.vimrc中加入如下的配置：
"-- QuickFix setting --
" 按下F6，执行make clean
map <F6> :make clean<CR><CR><CR>
" 按下F7，执行make编译程序，并打开quickfix窗口，显示编译信息
map <F7> :make<CR><CR><CR> :copen<CR><CR>
" 按下F8，光标移到上一个错误所在的行
map <F8> :cp<CR>
" 按下F9，光标移到下一个错误所在的行
map <F9> :cn<CR>
" 以上的映射是使上面的快捷键在插入模式下也能用
imap <F6> <ESC>:make clean<CR><CR><CR>
imap <F7> <ESC>:make<CR><CR><CR> :copen<CR><CR>
imap <F8> <ESC>:cp<CR>
imap <F9> <ESC>:cn<CR>

cs add /home/albert/Desktop/linux-2.6.38.2/cscope.out

set autoindent
set cindent
set mouse=a
