project('gtk-widget-demo', 'c',
  version : '0.1.0',
  default_options : ['warning_level=3'])

gtk4_dep = dependency('gtk4', include_type: 'system')
epoxy_dep = dependency('epoxy')
gallery_deps = [gtk4_dep, epoxy_dep]

inc = include_directories('include')

gallery_data_dir = meson.project_source_root() / 'data'
gallery_c_args = ['-DGALLERY_DATA_DIR="@0@"'.format(gallery_data_dir)]

main_sources = files(
  'src/main/about-dialog.c',
  'src/main/sample-palette.c',
  'src/main/window-shell.c',
)

gallery_sources = files(
  'src/gallery/button-demos.c',
  'src/gallery/button-demos/gtk-button-demo.c',
  'src/gallery/button-demos/gtk-check-button-demo.c',
  'src/gallery/button-demos/gtk-link-button-demo.c',
  'src/gallery/button-demos/gtk-lock-button-demo.c',
  'src/gallery/button-demos/gtk-menu-button-demo.c',
  'src/gallery/button-demos/gtk-radio-button-demo.c',
  'src/gallery/button-demos/gtk-switch-demo.c',
  'src/gallery/button-demos/gtk-toggle-button-demo.c',
  'src/gallery/button-demos/gtk-volume-button-demo.c',
  'src/gallery/container-demos.c',
  'src/gallery/demo-page.c',
  'src/gallery/demo-registry.c',
  'src/gallery/display-demos.c',
  'src/gallery/display-demos/gtk-calendar-demo.c',
  'src/gallery/display-demos/gtk-drawing-area-demo.c',
  'src/gallery/display-demos/gtk-emoji-chooser-demo.c',
  'src/gallery/display-demos/gtk-gl-area-demo.c',
  'src/gallery/display-demos/gtk-info-bar-demo.c',
  'src/gallery/display-demos/gtk-image-demo.c',
  'src/gallery/display-demos/gtk-label-demo.c',
  'src/gallery/display-demos/gtk-level-bar-demo.c',
  'src/gallery/display-demos/gtk-media-controls-demo.c',
  'src/gallery/display-demos/gtk-picture-demo.c',
  'src/gallery/display-demos/gtk-popover-menu-bar-demo.c',
  'src/gallery/display-demos/gtk-popover-menu-demo.c',
  'src/gallery/display-demos/gtk-progress-bar-demo.c',
  'src/gallery/display-demos/gtk-scale-demo.c',
  'src/gallery/display-demos/gtk-scrollbar-demo.c',
  'src/gallery/display-demos/gtk-separator-demo.c',
  'src/gallery/display-demos/gtk-spinner-demo.c',
  'src/gallery/display-demos/gtk-statusbar-demo.c',
  'src/gallery/display-demos/gtk-text-view-demo.c',
  'src/gallery/display-demos/gtk-video-demo.c',
  'src/gallery/display-demos/gtk-window-controls-demo.c',
  'src/gallery/entry-demos.c',
  'src/gallery/entry-demos/gtk-editable-label-demo.c',
  'src/gallery/entry-demos/gtk-entry-demo.c',
  'src/gallery/entry-demos/gtk-password-entry-demo.c',
  'src/gallery/entry-demos/gtk-search-entry-demo.c',
  'src/gallery/entry-demos/gtk-spin-button-demo.c',
  'src/gallery/gallery-shell.c',
  'src/gallery/window-demos.c',
)

introspection_core_sources = files(
  'src/introspection/type-ancestry.c',
  'src/introspection/property-list.c',
  'src/introspection/signal-list.c',
)

introspection_sources = introspection_core_sources + files(
  'src/introspection/inspector-pane.c',
  'src/introspection/inspector-pane/display.c',
  'src/introspection/inspector-pane/pick-mode.c',
  'src/introspection/inspector-pane/selection.c',
)

executable('gtk-widget-demo',
  'src/main.c',
  main_sources,
  gallery_sources,
  introspection_sources,
  include_directories : inc,
  c_args : gallery_c_args,
  dependencies : gallery_deps,
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

test_gallery_demo_registry = executable('test-gallery-demo-registry',
  'test/gallery/demo-registry.c',
  gallery_sources,
  include_directories : inc,
  c_args : gallery_c_args,
  dependencies : gallery_deps,
  install : false)

test_gallery_demo_builders = executable('test-gallery-demo-builders',
  'test/gallery/demo-builders.c',
  gallery_sources,
  include_directories : inc,
  c_args : gallery_c_args,
  dependencies : gallery_deps,
  install : false)

test_gallery_demo_page = executable('test-gallery-demo-page',
  'test/gallery/demo-page.c',
  gallery_sources,
  include_directories : inc,
  c_args : gallery_c_args,
  dependencies : gallery_deps,
  install : false)

test_gallery_demo_interactive = executable('test-gallery-demo-interactive',
  'test/gallery/demo-interactive.c',
  gallery_sources,
  include_directories : inc,
  c_args : gallery_c_args,
  dependencies : gallery_deps,
  install : false)

test_gallery_gallery_shell = executable('test-gallery-gallery-shell',
  'test/gallery/gallery-shell.c',
  gallery_sources,
  include_directories : inc,
  c_args : gallery_c_args,
  dependencies : gallery_deps,
  install : false)

test('introspection-type-ancestry', test_introspection_type_ancestry)
test('introspection-property-list', test_introspection_property_list)
test('introspection-signal-list', test_introspection_signal_list)
test('gallery-demo-registry', test_gallery_demo_registry)
test('gallery-demo-builders', test_gallery_demo_builders)
test('gallery-demo-page', test_gallery_demo_page)
test('gallery-demo-interactive', test_gallery_demo_interactive)
test('gallery-gallery-shell', test_gallery_gallery_shell)
