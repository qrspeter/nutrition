import pytest

import main

def test_positive():
    assert main.check_daily([2500, 100, 80, 400]), "Daily check error"
    
def test_negative():
    assert main.check_daily([100, 100, 800, 40]) == False, "Daily check error"
