package interfata;

import javax.swing.*;

public class QueryOutput extends JTextArea {

    public QueryOutput() {
        super();
        setEditable(false);
    }

    public void appendText(String text) {
        append(text);
    }
}
