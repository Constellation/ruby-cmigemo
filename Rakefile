# -*- ruby -*-
require 'rubygems'
require 'hoe'
require 'pp'

$version = '1.0.0'
$readme = 'README.rdoc'
$rdoc_opts = %W(--main #{$readme} --charset utf-8 --line-numbers)

Hoe.spec'cmigemo' do |p|
  developer('Constellation', 'utatane.tea@gmail.com')
  p.description = <<-EOF
  Ruby binding for C/Migemo
  use any encoding dictionary
  faster response
  EOF
  p.name = 'cmigemo'
  p.readme_file = $readme
  p.extra_rdoc_files = FileList[$readme]
  p.need_tar = false
  p.need_zip = false
  p.summary = 'Ruby binding for C/Migemo'
  p.test_globs = 'spec/**/*_spec.rb'
  p.url = 'http://github.com/Constellation/ruby-cmigemo'
  p.version = $version
  p.spec_extras[:extensions] = FileList["ext/extconf.rb"].to_a
  spec_extras[:rdoc_options] = $rdoc_opts
  #  p.spec_extras[:rdoc_options] = $rdoc_opts
  #p.clean_globs =
  # self.rubyforge_name = 'cmigemox' # if different than 'cmigemo'
end

ext = "ext"
ext_so = "ext/cmigemo.so"
ext_files = FileList[
  "ext/cmigemo.c",
  "ext/extconf.rb",
  "ext/Makefile",
  "lib"
]

# ext tasks
desc "build ext"
task :ext => ["ext/Makefile", ext_so]
file "ext/Makefile" => ["ext/extconf.rb"] do
  Dir.chdir(ext) do
    ruby "extconf.rb"
  end
end
file ext_so => ext_files do
  Dir.chdir(ext) do
    sh 'make'
  end
  cp ext_so, "lib"
end
directory "lib"

#namespace :dict do
#  desc "get cp932 dict"
#  task :cp932 do
#    puts "get cp932 dict"
#  end
#  desc "get utf-8 dict"
#  task :utf8 do
#    puts "get utf8 dict"
#  end
#  desc "get euc-jp dict"
#  task :eucjp do
#    puts "get eucjp dict"
#  end
#end


# vim: syntax=ruby
