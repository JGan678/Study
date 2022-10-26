public class Str {
    public static void main(String[] args) {
        String str = "hello1234";

        final int len = str.length();
        char[] tmp = new char[len];
        for (int i = 0; i < len; ++i)
            tmp[i] = str.charAt(i);

        for (int i = 0; i < len; ++i)
            switch (tmp[i]) {
                case '0':
                    tmp[i] = '1';
                    break;
                case '1':
                    tmp[i] = '2';
                    break;
                case '2':
                    tmp[i] = '3';
                    break;
                case '3':
                    tmp[i] = '4';
                    break;
                case '4':
                    tmp[i] = '5';
                    break;
                case '5':
                    tmp[i] = '6';
                    break;
                case '6':
                    tmp[i] = '7';
                    break;
                case '7':
                    tmp[i] = '8';
                    break;
                case '8':
                    tmp[i] = '9';
                    break;
                case '9':
                    tmp[i] = '0';
                    break;
            }

        String res = new String(tmp);
        System.out.println(res.toUpperCase());
    }
}
