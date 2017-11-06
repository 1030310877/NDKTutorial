package joe.com.ndktutorial;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import joe.com.ndktutorial.activity.Tutorial1Activity;
import joe.com.ndktutorial.activity.Tutorial2Activity;
import joe.com.ndktutorial.activity.Tutorial3Activity;
import joe.com.ndktutorial.activity.Tutorial4Activity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.tutorial_1).setOnClickListener(this);
        findViewById(R.id.tutorial_2).setOnClickListener(this);
        findViewById(R.id.tutorial_3).setOnClickListener(this);
        findViewById(R.id.tutorial_4).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent intent = null;
        switch (v.getId()) {
            case R.id.tutorial_1:
                intent = new Intent(this, Tutorial1Activity.class);
                break;
            case R.id.tutorial_2:
                intent = new Intent(this, Tutorial2Activity.class);
                break;
            case R.id.tutorial_3:
                intent = new Intent(this, Tutorial3Activity.class);
                break;
            case R.id.tutorial_4:
                intent = new Intent(this, Tutorial4Activity.class);
                break;
        }
        if (intent != null) {
            startActivity(intent);
        }
    }
}
