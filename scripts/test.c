int main(void) {
    printf("%s ABCDE\n", __func__);
    printf("%s 12345\n", __func__);
    printf("%s \nddddd\r\n\n", __func__);
    fprintf(stderr, "%s, df \n", __func__);
}
