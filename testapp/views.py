from testapp import app
from flask import render_template  # 追加

@app.route('/')
def index():
    return render_template('testapp/index.html')
@app.route('/recipes')
def other1():
    return render_template('testapp/index1.html')
@app.route('/faq')
def other2():
    return render_template('testapp/faq.html')
@app.route('/contacts')
def other3():
    return render_template('testapp/contacts.html')
@app.route('/about')
def other4():
    return render_template('testapp/about.html')