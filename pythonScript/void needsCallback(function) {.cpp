void needsCallback(int function) {
return function();
}
void number() {
 return 3;
}

int main() {
cout << needsCallback(number);
}