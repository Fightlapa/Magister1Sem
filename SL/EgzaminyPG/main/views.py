from django.shortcuts import render, redirect
from django.http import HttpRequest
from django.contrib import messages
from .models import ExamTemplates
from .forms import PGUserRegisterForm, ExamTemplateForm
from django.contrib.auth.decorators import login_required
from django.views.generic import ListView

# Create your views here.

def home(request):
    """Renders the home page."""
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/index.html',
        {
            'title':'Strona główna'
        }
    )

def register(request):
    """Renders the home page."""
    if request.method == 'POST':
        form = PGUserRegisterForm(request.POST)
        if form.is_valid():
            form.save()
            username = form.cleaned_data.get('username')
            messages.success(request, f'Stworzono użytkownika o nazwie {username}!')
            return redirect('main-login')
    else:
        form = PGUserRegisterForm()
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/register.html',
        {'form': form}
    )

@login_required
def exam_templates(request):
    """Renders the home page."""
    context = {
        'title':'Wzory egzaminów',
        'templates': ExamTemplates.objects.all()
    }
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/exam-templates.html',
        context
    )

def exam_list_view(ListView):
    model = ExamTemplates

@login_required
def create_exam_template(request):
    """Renders the home page."""
    if request.method == 'POST':
        form = ExamTemplateForm(request.POST, request.FILES)
        if form.is_valid():
            temporary = form.save(commit=False)
            temporary.teacher = request.user
            temporary.save()
            name = form.cleaned_data.get('name')
            messages.success(request, f'Stworzono wzór egzaminu o nazwie {name}!')
            return redirect('main-exam-templates')
    else:
        form = ExamTemplateForm()
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/create-exam-template.html',
        {'form': form}
    )

@login_required
def update_exam_template(request, exam_id):
    """Renders the home page."""
    if request.method == 'POST':
        form = ExamTemplateForm(request.POST, request.FILES, instance = ExamTemplates.objects.get(id=exam_id))
        if form.is_valid():
            temporary = form.save(commit=False)
            temporary.teacher = request.user
            temporary.save()
            name = form.cleaned_data.get('name')
            messages.success(request, f'Stworzono wzór egzaminu o nazwie {name}!')
            return redirect('main-exam-templates')
    else:
        form = ExamTemplateForm(instance = ExamTemplates.objects.get(id=exam_id))
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/update-exam-template.html',
        {'form': form}
    )

