package interfata;

import javax.swing.*;
import java.awt.*;

public class FirstTab extends JPanel {

    ViewToolbar viewToolbar;
    QueryOutput queryOutput;

    public FirstTab() {
        viewToolbar = new ViewToolbar();
        queryOutput = new QueryOutput();

        viewToolbar.setTypingListener(text -> queryOutput.appendText(text));

        setLayout(new BorderLayout());
        add(viewToolbar, BorderLayout.NORTH);
        add(new JScrollPane(queryOutput), BorderLayout.CENTER);
    }
}
