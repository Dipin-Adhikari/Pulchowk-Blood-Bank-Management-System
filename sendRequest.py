import smtplib
import sys
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from dotenv import load_dotenv
import os

def main():
    if len(sys.argv) > 1:
        mailID = sys.argv[1]
        bloodType = sys.argv[2]
        pint = int(sys.argv[3])
        date = sys.argv[4]
        time = sys.argv[5]


        load_dotenv()

        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        serverMail = 'bloodbank.pcampus@gmail.com'
        serverPass = os.getenv('gmailPass')
        server.login(serverMail, serverPass)
        message = MIMEMultipart()
        message["From"] = serverPass
        message["To"] = mailID
        message["Subject"] = f"{bloodType} blood Request"
        body = f"We need {pint} pint of {bloodType} blood on {date} at {time}. If you are available, then please contact us."
        message.attach(MIMEText(body, "plain"))
        server.sendmail(serverMail,
                 mailID,
                 message.as_string())


if __name__ == "__main__":
    main()

