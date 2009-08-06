require 'mkmf'

have_header('migemo.h');
have_library('migemo');

create_makefile('cmigemo');
