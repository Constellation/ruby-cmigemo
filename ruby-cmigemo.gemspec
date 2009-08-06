# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{cmigemo}
  s.version = "1.0.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Constellation"]
  s.date = %q{2009-08-06}
  s.description = %q{  Ruby binding for C/Migemo
  use any encoding dictionary
  faster response
}
  s.email = ["utatane.tea@gmail.com"]
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = ["History.txt", "Manifest.txt", "README.rdoc"]
  s.files = ["History.txt", "Manifest.txt", "README.rdoc", "Rakefile", "ext/cmigemo.c", "ext/extconf.rb", "test/test_cmigemo.rb"]
  s.homepage = %q{http://github.com/Constellation/ruby-cmigemo}
  s.rdoc_options = ["--main", "README.rdoc", "--charset", "utf-8", "--line-numbers"]
  s.require_paths = ["lib", "ext"]
  s.rubyforge_project = %q{cmigemo}
  s.rubygems_version = %q{1.3.5}
  s.summary = %q{Ruby binding for C/Migemo}

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 3

    if Gem::Version.new(Gem::RubyGemsVersion) >= Gem::Version.new('1.2.0') then
      s.add_development_dependency(%q<hoe>, [">= 2.3.2"])
    else
      s.add_dependency(%q<hoe>, [">= 2.3.2"])
    end
  else
    s.add_dependency(%q<hoe>, [">= 2.3.2"])
  end
end
