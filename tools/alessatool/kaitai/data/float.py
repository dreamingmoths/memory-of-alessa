from ctypes import c_float
from math import copysign

def find_smallest_float_string(f: float):
    '''
    Try to minimize the length of a decimal string representing a float.
    
    a slow, silly way

    see libalessaformat for a better way!
    '''
    float_string = str(f)
    f32 = c_float(f)

    sign_value = copysign(1, f)
    sign_symbol = sign_value < 0 and "-" or ""

    if f32.value == 0:
        return f"{sign_symbol}0.0f"

    assert f32.value == c_float(f).value

    size = len(float_string)
    for i in range(len(float_string), 0, -1):
        candidate = float_string[:i]
        if candidate == "-": continue
        try:
            if c_float(float(candidate)).value != f32.value:
                break
        except:
            break
        size = i

    result = float_string[:size]

    match result:
        case "3.1415927":
            return "PI"
        case "-3.1415927":
            return "-PI"
        case "1.57079637":
            return "QUARTER_TURN"
        case "-1.57079637":
            return "-QUARTER_TURN"

    if not result.startswith(sign_symbol):
        result = sign_symbol + result

    return end_float_string(result)

def end_float_string(result: str):
    if "." not in result:
        result += ".0"

    return result + "f"
