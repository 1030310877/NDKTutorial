package joe.com.ndktutorial;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import joe.com.ndktutorial.activity.Tutorial1Activity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.tutorial_1).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent intent = null;
        switch (v.getId()) {
            case R.id.tutorial_1:
                intent = new Intent(this, Tutorial1Activity.class);
                break;
        }
        if (intent != null) {
            startActivity(intent);
        }
    }
}
