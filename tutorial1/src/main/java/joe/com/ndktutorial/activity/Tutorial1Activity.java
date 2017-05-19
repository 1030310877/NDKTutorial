package joe.com.ndktutorial.activity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import joe.com.ndktutorial.R;

/**
 * Created by joe on 2017/5/19.
 */
public class Tutorial1Activity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_1);
        TextView strTv = (TextView) findViewById(R.id.new_str);
        TextView intTv = (TextView) findViewById(R.id.new_int);
        TextView booleanTv = (TextView) findViewById(R.id.new_boolean);
        TextView intArrayTv = (TextView) findViewById(R.id.new_int_array);
        TextView objectTv = (TextView) findViewById(R.id.new_object);
        strTv.setText(newStringFromJNI());
        intTv.setText(String.valueOf(newIntFromJNI()));
        booleanTv.setText(String.valueOf(newBooleanFromJNI()));
        int[] array = newIntArrayFromJNI();
        StringBuilder builder = new StringBuilder();
        for (int i : array) {
            builder.append(i).append("  ");
        }
        intArrayTv.setText(builder.toString());
        TestObject object = newTestObjectFromJNI();
        if (object != null) {
            objectTv.setText(object.toString());
        } else {
            objectTv.setText("出现错误，未能生成");
        }
    }

    public class TestObject {
        public TestObject() {
        }

        private int arg = 0;
        private String tag = "This is TestObject";

        public int getArg() {
            return arg;
        }

        public void setArg(int arg) {
            this.arg = arg;
        }

        public String getTag() {
            return tag;
        }

        public void setTag(String tag) {
            this.tag = tag;
        }

        public String toString() {
            return tag + " " + arg;
        }
    }

    static {
        System.loadLibrary("base-lib");
    }

    private native String newStringFromJNI();

    private native int newIntFromJNI();

    private native boolean newBooleanFromJNI();

    private native int[] newIntArrayFromJNI();

    private native TestObject newTestObjectFromJNI();
}
