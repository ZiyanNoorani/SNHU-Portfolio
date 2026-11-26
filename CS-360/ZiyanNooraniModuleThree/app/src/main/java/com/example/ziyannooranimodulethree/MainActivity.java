package com.example.ziyannooranimodulethree;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

/**
 * Module Five: greets the user by name.
 * The Say Hello button stays disabled until the user types a name.
 */
public class MainActivity extends AppCompatActivity {

    private EditText nameText;
    private TextView textGreeting;
    private Button buttonSayHello;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        nameText = findViewById(R.id.nameText);
        textGreeting = findViewById(R.id.textGreeting);
        buttonSayHello = findViewById(R.id.buttonSayHello);

        // Matches android:enabled="false" in activity_main.xml, so the
        // button starts disabled even if the layout attribute is changed later.
        buttonSayHello.setEnabled(false);

        // Enable the button only while nameText holds a real name.
        nameText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                // Not needed
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                buttonSayHello.setEnabled(hasName(s));
            }

            @Override
            public void afterTextChanged(Editable s) {
                // Not needed
            }
        });

        // Pressing Done on the keyboard works the same as tapping the button.
        // Returning false lets Android close the keyboard as usual.
        nameText.setOnEditorActionListener((v, actionId, event) -> {
            if (actionId == EditorInfo.IME_ACTION_DONE && buttonSayHello.isEnabled()) {
                SayHello(v);
            }
            return false;
        });
    }

    /**
     * Writes "Hello" and the contents of nameText to textGreeting.
     * Called by android:onClick="SayHello" on buttonSayHello.
     *
     * @param view the view that was clicked
     */
    public void SayHello(View view) {
        // Validation: stop if the field or its text is null.
        if (nameText == null || nameText.getText() == null) {
            return;
        }

        // Validation: stop if the user typed only spaces.
        String name = nameText.getText().toString().trim();
        if (name.isEmpty()) {
            return;
        }

        textGreeting.setText(getString(R.string.greeting_format, name));
    }

    /**
     * Returns true when the text contains at least one non-space character.
     */
    private static boolean hasName(CharSequence text) {
        return text != null && text.toString().trim().length() > 0;
    }
}