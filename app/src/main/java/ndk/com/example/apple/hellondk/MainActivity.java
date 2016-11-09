package ndk.com.example.apple.hellondk;

import android.app.Activity;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity {
    Button btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8;

    private User user = new User();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btn1 = (Button) findViewById(R.id.btn1);
        btn2 = (Button) findViewById(R.id.btn2);
        btn3 = (Button) findViewById(R.id.btn3);
        btn4 = (Button) findViewById(R.id.btn4);
        btn5 = (Button) findViewById(R.id.btn5);
        btn6 = (Button) findViewById(R.id.btn6);
        btn7 = (Button) findViewById(R.id.btn7);
        btn8 = (Button) findViewById(R.id.btn8);
    }

    public native String strFromNdk();

    public native String passStr(String javastr);

    public native int add(int x, int y);

    static {
        System.loadLibrary("hello-ndk");
    }

    public void strFromNdk(View view) {
        btn1.setText(strFromNdk());
    }

    public void passStr(View view) {
        String strFromNdk = passStr("String from Java");
        Toast.makeText(this, strFromNdk, Toast.LENGTH_SHORT).show();
    }

    public void addInt(View view) {
        int x = 10;
        int y = 5;
        int sum = add(x, y);
        Toast.makeText(this, x + " + " + y + "=" + sum, Toast.LENGTH_SHORT).show();
    }

    public native void callCode();//只为触发ndk调用Java方法

    public native void callCode1();//只为触发ndk调用Java方法

    public native void callCode2();//只为触发ndk调用Java方法

    public native void callCode3();//只为触发ndk调用Java方法

    ///C调用java中的空方法
    public void helloFromJava() {
        Toast.makeText(this, "called java method by ndk", Toast.LENGTH_SHORT).show();
    }

    public void printString(String s) {
        Toast.makeText(this, "in java code " + s, Toast.LENGTH_SHORT).show();
    }

    public void callJava(View view) {
        callCode();
    }

    public void callJavaStr(View view) {
        callCode1();
    }

    public void callJavaAdd(View view) {
        callCode2();
    }

    public native void fillUser(User user);

    public void notifyOk() {
        Toast.makeText(this, "user:" + user, Toast.LENGTH_SHORT).show();
    }

    public void modifyByNdk(View view) {
        fillUser(user);
    }

    public void throwException(View view) {
        callCode3();
    }

    public void initUninstallObserver(View view) {
        initUninstallObserver(Build.VERSION.SDK_INT, "http://www.baidu.com");
    }

    private final String TAG = getClass().getSimpleName();//13231922788


    public native void initUninstallObserver(int version, String url);


}
