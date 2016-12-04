if (expand("%:e") == "gramz")
  source ~/.vim/bundle/rainbow/plugin/rainbow.vim
  RainbowToggle
  syntax match dot /:/
  syntax match quote /'/
  syntax match bracket /<\(>\@!.\)*>/

  syntax match grammar /\[.-.\]/
  syntax match grammar /\./
  syntax match char /'.'/
  syntax match char /"\("\@!.\)*"/
  syntax match escape /\\'\@!./
  syntax match comment /^#.*$/
  syntax match quantifier /\*\|?\|-\|!\|+\||\|\./

  highlight Normal ctermfg=33
  highlight dot ctermfg=white
  highlight quantifier ctermfg=yellow
  highlight grammar ctermfg=brown
  highlight escape ctermfg=red
  highlight comment ctermfg=59
  highlight char ctermfg=cyan
  highlight quote ctermfg=cyan
  highlight bracket ctermfg=grey
endif
