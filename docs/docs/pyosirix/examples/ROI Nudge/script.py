import sys

import osirix
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QHBoxLayout, QGridLayout, QSlider, QLabel, QLineEdit, QCheckBox, QMessageBox, QDialog
from PyQt5.QtCore import Qt, QTimer

class InfoDialog(QDialog):
    """ A Simple model dialog for the user.

    """
    def __init__(self, message, parent=None):
        super().__init__(parent)

        self.setWindowTitle("Information")

        # Create layout
        layout = QVBoxLayout()

        # Create and add label with the message
        self.message_label = QLabel(message, self)
        layout.addWidget(self.message_label)

        # Create and add OK button
        self.ok_button = QPushButton("OK", self)
        self.ok_button.clicked.connect(self.accept)
        layout.addWidget(self.ok_button)

        self.setLayout(layout)

        # Set window properties
        self.setModal(True)
        self.resize(300, 150)


class ROIMoveWidget(QWidget):
    def __init__(self, viewer):
        super().__init__()

        self.viewer = viewer
        self.initUI()

    def initUI(self):
        # Create buttons
        self.up_button = QPushButton("↑", self)
        self.down_button = QPushButton("↓", self)
        self.left_button = QPushButton("←", self)
        self.right_button = QPushButton("→", self)
        ok_button = QPushButton("OK", self)

        # Create a slider
        self.slider = QSlider(Qt.Horizontal, self)
        self.slider.setMinimum(1)
        self.slider.setMaximum(10)
        self.slider.setValue(5)
        self.slider.setTickPosition(QSlider.TicksBelow)
        self.slider.setTickInterval(1)

        # Create a text box to display the slider value
        self.text_box = QLineEdit(self)
        self.text_box.setReadOnly(True)
        self.text_box.setText(str(self.slider.value()))

        # Create a label for the text box
        self.label = QLabel("Pixels shift", self)

        # Connect slider to function to update the text box
        self.slider.valueChanged.connect(self.updateTextBox)

        # Connect buttons to functions
        self.up_button.pressed.connect(lambda: self.startRepeating("Up"))
        self.down_button.pressed.connect(lambda: self.startRepeating("Down"))
        self.left_button.pressed.connect(lambda: self.startRepeating("Left"))
        self.right_button.pressed.connect(lambda: self.startRepeating("Right"))

        self.up_button.released.connect(self.stopRepeating)
        self.down_button.released.connect(self.stopRepeating)
        self.left_button.released.connect(self.stopRepeating)
        self.right_button.released.connect(self.stopRepeating)

        ok_button.clicked.connect(lambda: self.buttonClicked("OK"))

        # Create layout and add buttons
        grid_layout = QGridLayout()
        grid_layout.addWidget(self.up_button, 0, 1)
        grid_layout.addWidget(self.left_button, 1, 0)
        grid_layout.addWidget(self.right_button, 1, 2)
        grid_layout.addWidget(self.down_button, 2, 1)

        # Layout for label and text box
        label_text_layout = QHBoxLayout()
        label_text_layout.addWidget(self.label)
        label_text_layout.addWidget(self.text_box)

        # Main layout
        main_layout = QVBoxLayout()
        main_layout.addLayout(grid_layout)
        main_layout.addWidget(self.slider)
        main_layout.addLayout(label_text_layout)

        # Add OK and Cancel buttons at the bottom
        bottom_layout = QHBoxLayout()
        bottom_layout.addWidget(ok_button)
        main_layout.addLayout(bottom_layout)

        # Set layout for the main widget
        self.setLayout(main_layout)

        # Set window properties - keep it on top!
        self.setWindowTitle("Move ROIs")
        self.setWindowFlags(self.windowFlags() | Qt.WindowStaysOnTopHint)
        self.show()

        # Timer for button repeat functionality
        self.timer = QTimer()
        self.timer.timeout.connect(self.repeatAction)
        self.current_action = None

    def startRepeating(self, direction):
        self.current_action = direction
        self.timer.start(100)  # Repeat every 100 milliseconds

    def stopRepeating(self):
        self.timer.stop()
        self.current_action = None

    def repeatAction(self):
        if self.current_action:
            self.buttonClicked(self.current_action)

    def buttonClicked(self, label):
        if label in ["Up", "Down", "Left", "Right"]:
            shift = self.slider.value()
            for roi in self.viewer.selected_rois():
                if label == "Up":
                    roi.roi_move(0, -shift)
                elif label == "Down":
                    roi.roi_move(0, shift)
                elif label == "Left":
                    roi.roi_move(-shift, 0)
                else:
                    roi.roi_move(shift, 0)

        if label == "OK":
            self.close()

    def updateTextBox(self):
        self.text_box.setText(str(self.slider.value()))

if __name__ == '__main__':
    app = QApplication(sys.argv)

    viewer = None
    try:
        viewer = osirix.frontmost_viewer()
    except osirix.exceptions.GrpcException:
        dialog = InfoDialog("No OsiriX viewer found!")
        dialog.exec_()
        sys.exit(0)
        sys.exit(0)

    ex = ROIMoveWidget(viewer)
    sys.exit(app.exec_())
