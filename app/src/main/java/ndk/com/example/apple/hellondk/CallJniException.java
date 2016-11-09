package ndk.com.example.apple.hellondk;

/**
 * Created by apple on 16-2-19.
 */

/**
 * 自定义的一个异常，用于封装调用JNI端时发生的异常信息
 */
public class CallJniException extends RuntimeException {

    private static final long serialVersionUID = 1L;

    public CallJniException(String message) {

        super(message);
    }

}
