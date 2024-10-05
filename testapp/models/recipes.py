from testapp import db
from datetime import datetime


class recipe(db.Model):
    __tablename__ = 'recipe'
    id = db.Column(db.Integer, primary_key=True)  # システムで使う番号
    name = db.Column(db.String(255))  # 料理名
    times = db.Column(db.String(255))  # かかる時間
    diff = db.Column(db.String(255))
