'''
py.test -sv -k test_login
'''
import pytest
import os
import sys
from errno import EPERM

cur = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(os.path.dirname(cur), 'python'))

hello = pytest.importorskip("hello")

@pytest.fixture(scope='function')
def suit():
    #some setup code
    sys.argv = ["hello_test"]

def test_zero(suit, capsys):
    with pytest.raises(SystemExit) as err:
        hello.main()
    assert 2 == err.value.code
    _, err = capsys.readouterr()
    assert "error: too few arguments" in err, err

def test_version(suit, capsys):
    sys.argv.append("-v")
    assert 0 == hello.main()
    out, _ = capsys.readouterr()
    assert "0.0.1" in out, out

def test_login(suit, capsys):
    assert EPERM == hello.login()
    out, err = capsys.readouterr()
    assert len(out) == 0
    assert "user login failed" in err, err

def test_login_wrong(suit, capsys):
    assert EPERM == hello.login('hello','world')
    out, err = capsys.readouterr()
    assert len(out) == 0
    assert "user login failed" in err, err

def test_login_c(suit, capsys):
    assert 0 == hello.login('hello','hello')
    out, err = capsys.readouterr()
    assert len(out) == 0
    assert len(err) == 0

def test_hello(suit, capsys):
    sys.argv.extend(["-vv","hello"])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "hello" in out, out
    assert len(err) == 0

def test_add_zero(suit, capsys):
    sys.argv.extend(["-vv","add"])
    with pytest.raises(SystemExit) as err:
        hello.main()
    assert 2 == err.value.code
    _, err = capsys.readouterr()
    assert "error: too few arguments" in err, err

def test_add_one(suit, capsys):
    sys.argv.extend(["-vv","add",'8'])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "8" in out, out
    assert len(err) == 0

def test_add_two(suit, capsys):
    sys.argv.extend(["-vv","add",'8','18'])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "26" in out, out
    assert len(err) == 0

def test_add_multi(suit, capsys):
    sys.argv.extend(["-vv","add",'8','18','5','67'])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "98" in out, out
    assert len(err) == 0

def test_split_zero(suit, capsys):
    sys.argv.extend(["-vv","split"])
    with pytest.raises(SystemExit) as err:
        hello.main()
    assert 2 == err.value.code
    _, err = capsys.readouterr()
    assert "error: too few arguments" in err, err

def test_split_no(suit, capsys):
    sys.argv.extend(["-vv","split","teststr"])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "teststr" in out, out
    assert len(err) == 0

def test_split_ok1(suit, capsys):
    sys.argv.extend(["-vv","split","teststr;testdir;hello"])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "teststr testdir hello" in out, out
    assert len(err) == 0

def test_split_ok2(suit, capsys):
    sys.argv.extend(["-vv","split","teststr.testdir,hello"])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "teststr testdir hello" in out, out
    assert len(err) == 0

def test_split_ok3(suit, capsys):
    sys.argv.extend(["-vv","split","teststr.-;testdir,; hello"])
    assert 0 == hello.main()
    out, err = capsys.readouterr()
    assert "teststr   testdir   hello" in out, out
    assert len(err) == 0
