project('gtk-widget-demo', 'c',
  version : '0.1.0',
  default_options : ['warning_level=3'])

gtk4_dep = dependency('gtk4', include_type: 'system')

executable('gtk-widget-demo',
  'src/main.c',
  dependencies : gtk4_dep,
  install : false)
