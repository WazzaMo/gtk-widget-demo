project('gtk-widget-demo', 'c',
  version : '0.1.0',
  default_options : ['warning_level=3'])

gtk4_dep = dependency('gtk4', include_type: 'system')

inc = include_directories('include')

introspection_core_sources = files(
  'src/introspection/type-ancestry.c',
  'src/introspection/property-list.c',
  'src/introspection/signal-list.c',
)

introspection_sources = introspection_core_sources + files(
  'src/introspection/inspector-pane.c',
)

executable('gtk-widget-demo',
  'src/main.c',
  introspection_sources,
  include_directories : inc,
  dependencies : gtk4_dep,
  install : false)

test_introspection = executable('test-introspection',
  'test/introspection/test-type-ancestry.c',
  introspection_core_sources,
  include_directories : inc,
  dependencies : gtk4_dep,
  install : false)

test('introspection', test_introspection)
