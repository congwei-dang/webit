

#include <stdio.h>

namespace UvoicInc {


void test1() {
    printf("test1.\n");
}


class UvoicInitializer {

public:
	UvoicInitializer() {
		
	}
};

UvoicInitializer the_initializer;

} // namespace UvoicInc

