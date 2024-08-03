from math import cos, pi

# TODO: Convert this code to use q format precision

def main(f, PRECISION, NAME):
    f.write("double %s[] = {\n" % NAME)
    j = 0
    p = 0.0
    while True:
        f.write("{:.20f}, ".format(cos(p)))
        j += 1
        p += PRECISION
        if p > 2*pi:
            break
    f.write("1.0 };\n")
    f.write("const int %s_size = %d;\n" % (NAME, j+1))


if __name__ == '__main__':
    main(open("./lib/table/costable_1.h", "w"), 1.0, "costable_1")
    main(open("./lib/table/costable_0_1.h", "w"), 0.1, "costable_0_1")
    main(open("./lib/table/costable_0_01.h", "w"), 0.01, "costable_0_01")
    main(open("./lib/table/costable_0_001.h", "w"), 0.001, "costable_0_001")
    main(open("./lib/table/costable_0_0001.h", "w"), 0.0001, "costable_0_0001")