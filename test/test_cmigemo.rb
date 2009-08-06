require File.dirname(__FILE__) + '/../lib/cmigemo'
$KCODE = 'u'
class TestCmigemo < Test::Unit::TestCase

  def setup
    @cmigemo = CMigemo::new
    d = File.expand_path(File.join(File.dirname(__FILE__), '../dict/utf-8'))
    @dicts = {
      File.join(d, "migemo-dict")   => CMigemo::MIGEMO,
      File.join(d, "han2zen.dat")   => CMigemo::HAN2ZEN,
      File.join(d, "hira2kata.dat") => CMigemo::HIRA2KATA,
      File.join(d, "roma2hira.dat") => CMigemo::ROMA2HIRA,
    }
  end

  def test_new
    assert_instance_of CMigemo, @cmigemo
  end

  def load_dicts c=@cmigemo
    @dicts.each do |dict, type|
      c.load(type, dict)
    end
  end

  def test_query
    load_dicts
    reg = Regexp.new(@cmigemo.query 'seiza')
    assert reg =~ "正座"
    assert reg =~ "星座"
  end

  def test_close
    cmigemo = CMigemo::new
    cmigemo.close
    assert_raise Exception do
      cmigemo.query 'seiza'
    end
  end

end
