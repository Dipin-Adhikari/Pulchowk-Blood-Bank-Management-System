import smtplib
import sys
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from dotenv import load_dotenv
import os

def main():
    if len(sys.argv) > 1:
        mailID = sys.argv[1]
        otp = int(sys.argv[2])

        load_dotenv()

        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        serverMail = '080bei015.dipin@pcampus.edu.np'
        serverPass = os.getenv('gmailPass')
        server.login(serverMail, serverPass)
        message = MIMEMultipart()
        message["From"] = serverPass
        message["To"] = mailID
        message["Subject"] = "Pulchowk Blood Bank Verification Code"
        body = f"Verify your Pulchowk Blood Bank Email Address\n\nHi there,\nThank you for registering on Pulchowk Blood Bank Management System.\n\nWe want to make sure it's really you. Please enter the following verification code. If you didn't signup for Pulchowk Blood Bank, ignore this email.\n\nVerification Code: \n{otp}\n\nThis code will expire 10 minutes after it was sent.  "
        message.attach(MIMEText(body, "plain"))
        server.sendmail(serverMail,
                 mailID,
                 message.as_string())


if __name__ == "__main__":
    main()


