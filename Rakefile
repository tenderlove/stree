# -*- ruby -*-

require 'rubygems'
require 'hoe'

HOE = Hoe.spec 'stree' do
  developer('Aaron Patterson', 'aaron@tenderlovemaking.com')
  self.readme_file   = 'README.rdoc'
  self.history_file  = 'CHANGELOG.rdoc'
  self.extra_rdoc_files  = FileList['*.rdoc']
  self.extra_dev_deps << ['rake-compiler', '>= 0']
  self.spec_extras = { :extensions => ["ext/stree/extconf.rb"] }
end

require "rake/extensiontask"

Rake::ExtensionTask.new(HOE.name, HOE.spec) do |ext|
  ext.lib_dir = File.join('lib', 'stree')
end

Rake::Task[:test].prerequisites << :compile

# vim: syntax=ruby
