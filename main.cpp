/**
 * @brief AFL fuzz tester demonstration program
 * @author Wolfram Rösler <wolfram@roesler-ac.de>
 * @date 2017-05-24
 */

#include <fstream>
#include <iostream>

/**
 * URI decoder.
 * Translates %xx (xx = two hex digits) to the character with the
 * appropriate ASCII code. Translates '+' into space. Leaves all
 * other characters unchanged.
 *
 * Example:
 * - In:  "Hello+world%21"
 * - Out: "Hello world!"
 *
 * @param s The string to decode.
 * @returns The decoded string.
 * @bug Buggy by design.
 */
const char *uridecode(const char *s) {
	static char ret[100];
	for(auto *p=ret;*s;++s) {
		if (*s=='%') {
			auto const a = *++s;
			auto const b = *++s;
			*p++ = (a<='9' ? a-'0' : a-'a') * 16 + (b<='9' ? b-'0' : b-'a');
		} else if (*s=='+') {
			*p++ = ' ';
		} else {
			*p++ = *s;
		}
	}

	return ret;
}

/*
 * Test program.
 * Reads a pattern from stdin, decodes it, and writes the
 * result to stdout.
 */
int main() {
	auto const uri = std::string(
		std::istreambuf_iterator<char>(std::cin),
		std::istreambuf_iterator<char>()
	);
	std::cout << uridecode(uri.c_str());
}
