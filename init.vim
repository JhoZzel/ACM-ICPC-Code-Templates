"========== Plugins ================
call plug#begin('~/.vim/plugged')
 
    "Plug 'sainnhe/gruvbox-material'
    Plug 'jiangmiao/auto-pairs'
    Plug 'joshdick/onedark.vim'         "tema
    Plug 'vim-airline/vim-airline-themes'    "temas para el vim-airline
    Plug 'searleser97/cpbooster.vim'

call plug#end()

" ======== Configuracion del tema ============
" set background=dark
" let g:gruvbox_material_background='medium'
" colorscheme gruvbox-material
set termguicolors             "activa el true color en la terminal
colorscheme onedark             "activar el tema onedark

" ======== Configuraciones básicas ============
syntax on
set mouse=a
set number
set showcmd
set encoding=utf-8
set showmatch
set tabstop=4
set shiftwidth=4
set expandtab
filetype plugin indent on
set clipboard=unnamedplus " Se mantiene la copia en el portapapeles

" Atajos
command! -range=% Cp <line1>,<line2>w !xclip -selection clipboard



" ===================== FUNCIONES UTILES =====================
" Crea por defecto el archivo a partir de una plantilla
"function AddTemplate(tmpl_file)
"    exe "0read " . a:tmpl_file
"    let substDict = {}
"    let substDict["name"] = $USER
"    let substDict["date"] = strftime("%Y %b %d %X")
    " exe '%s/<<\([^>]*\)>>/\=substDict[submatch(1)]/g'
"    set nomodified
"    50
"endfunction

" autocmd BufNewFile *.c,*.cc,*.cpp,*.h call AddTemplate("~/templates/base.cpp")

" Compile and run C++ program in subshell
function! CompileAndRun()
  let fileName = expand('%')
  if fileName =~ '\.cpp$'
    let exeName = 'a.out'
    execute 'w | !g++ -std=c++20 -Wall -Wextra -Wpedantic -O2 -o ' . exeName . ' ' . fileName
    if v:shell_error == 0
      let cmd = "x-terminal-emulator -e bash -c './" . exeName . "; read -p \"\nPress enter to exit...\"'"
      call system(cmd)
      redraw!
    endif
  else
    echo 'Not a C++ file'
  endif
endfunction

" Compile and run C++ program with input from in.txt in subshell
function! CompileAndRunInTXT()
  let fileName = expand('%')
  if fileName =~ '\.cpp$'
    let exeName = 'a.out'
    let outputFile = 'out' " Nombre del archivo de salida
    let dbgFile = 'dbg'  " Nombre del archivo de salida para mensajes de depuración

    " Eliminar el archivo de salida si ya existe
    silent! execute '!rm ' . outputFile

    " Comando de compilación
    let compileCmd = 'g++ -std=c++20 -Wall -Wextra -Wpedantic -O2 -o ' . exeName . ' ' . fnameescape(fileName)

    " Compilar el programa
    let compileOutput = system(compileCmd)

    " Verificar si la compilación tuvo éxito
    if v:shell_error == 0
      " Ejecutar el programa y redirigir la entrada y salida estándar
      let runCmd = './' . exeName . ' < in > ' . outputFile . ' 2> ' . dbgFile
      call system(runCmd)

      redraw!  " Redraw para limpiar la pantalla

      echo 'Archivo de salida generado correctamente'
    else
      " Mostrar mensajes de error de compilación
      redraw!  " Redraw para limpiar la pantalla
      echohl ErrorMsg
      echomsg 'Error de compilación:'
      echomsg compileOutput
      echohl None
    endif
  else
    echo 'Not a C++ file'
  endif
endfunction




" Map keys to compile and run current file
map <F5> :call CompileAndRun()<CR>
map <F9> :w<CR>:!clear<CR>:call CompileAndRun()<CR>
map <F6> :call CompileAndRunInTXT()<CR>

"-----------------------------------------------------------------------------------

" Mapeo para cambiar a la pestaña siguiente o anterior
nnoremap <Tab> :tabnext<CR>
nnoremap <S-Tab> :tabprev<CR>

" Mapeo para crear un nuevo archivo usando una plantilla específica
nnoremap <Leader>cpp :call CreateNewFile()<CR>

function! CreateNewFile()
  let filename = input("Nombre del nuevo archivo: ")
  let template = input("Nombre de la plantilla en templates: ")
  execute 'e ' . filename 
  " execute 'read ~/templates/' . template
  execute 'read /home/jhozzel/Github/ACM-ICPC-Code-Templates/_templates_/' . template
endfunction
