# از ایمیج پایه Python استفاده می‌کنیم
FROM python:latest

RUN apt-get update && apt-get install -y \
    iputils-ping
# تنظیم پوشه کاری و کپی کدهای سرور به کانتینر
WORKDIR /srv/app
COPY . .

# نصب کتابخانه zmq برای Python
RUN pip install --root-user-action=ignore -r requirements.txt
# اجرای کد سرور
CMD ["python","server.py"]
