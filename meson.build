project('gtk-widget-demo', 'c',
  version : '0.1.0',
  default_options : ['warning_level=3'])

gtk4_dep = dependency('gtk4', include_type: 'system')

inc = include_directories('include')

main_sources = files(
  'src/main/sample-palette.c',
  'src/main/window-shell.c',
)

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
  main_sources,
  introspection_sources,
  include_directories : inc,
  dependencies : gtk4_dep,
  install : false)

test_introspection_type_ancestry = executable('test-introspection-type-ancestry',
  'test/introspection/type-ancestry.c',
  'src/introspection/type-ancestry.c',
  include_directories : inc,
  dependencies : gtk4_dep,
  install : false)

test_introspection_property_list = executable('test-introspection-property-list',
  'test/introspection/property-list.c',
  'src/introspection/property-list.c',
  include_directories : inc,
  dependencies : gtk4_dep,
  install : false)

test_introspection_signal_list = executable('test-introspection-signal-list',
  'test/introspection/signal-list.c',
  'src/introspection/signal-list.c',
  include_directories : inc,
  dependencies : gtk4_dep,
  install : false)

test('introspection-type-ancestry', test_introspection_type_ancestry)
test('introspection-property-list', test_introspection_property_list)
test('introspection-signal-list', test_introspection_signal_list)
