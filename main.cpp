#include "tcpconnection.h"

bool prime(size_t i) {
    for (size_t j=2; j*j<=i; j++) {
        if (i%j==0) return false;
    }
    return true;
}

int main() {
    TcpConnection c; c.open("localhost","4444");

    for (size_t i=1; i<100; i++) {
        if (c.available()) {
            cout << "Testing " << i;
            cout << " expected: ";
            string expected = (prime(i) ? "PRIME" : "NOT_PRIME");
            cout << expected;
            string actual = c.send_data(i);
            cout << " actual: " << actual;
            cout << ((expected == actual) ? " Passed" : " FAIL!");
            cout << endl;
            flush(cout);
        }
    }
    c.close();
    return 0;
}