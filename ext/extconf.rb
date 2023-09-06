require 'mkmf'

extension_name = 'example'
dir_config(extension_name)

unless have_library('c')
  abort 'Could not find required C library'
end

create_makefile(extension_name)

