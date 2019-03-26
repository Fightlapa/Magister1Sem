from django.shortcuts import render, redirect
from django.http import HttpRequest
from django.contrib import messages
from django.contrib.auth.mixins import LoginRequiredMixin, UserPassesTestMixin
from .models import ExamTemplates
from .forms import PGUserRegisterForm
from django.contrib.auth.decorators import login_required
# default template for these classes are: app/modelname_method.html
from django.views.generic import ListView, DetailView, CreateView, UpdateView, DeleteView
from django.utils import timezone

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

class exam_list_view(LoginRequiredMixin, ListView):
    model = ExamTemplates
    template_name = 'app/exam-templates.html'
    context_object_name = 'templates' # name of collection seen in template
    ordering = ['-date_modified']
    paginate_by = 3

class exam_detail_view(LoginRequiredMixin, DetailView):
    model = ExamTemplates
    template_name = 'app/exam-template-detail.html'

class exam_create_view(LoginRequiredMixin, CreateView):
    model = ExamTemplates
    template_name = 'app/create-exam-template.html'
    fields = ['name', 'image']

    def form_valid(self, form):
        form.instance.teacher = self.request.user
        return super().form_valid(form)


class exam_update_view(LoginRequiredMixin, UserPassesTestMixin, UpdateView):
    model = ExamTemplates
    template_name = 'app/update-exam-template.html'
    fields = ['name', 'image']

    def form_valid(self, form):
        form.instance.teacher = self.request.user
        form.instance.date_modified = timezone.now
        return super().form_valid(form)

    # If authorized
    def test_func(self):
        exam_template = self.get_object()
        if self.request.user == exam_template.teacher:
            return True
        return False

class exam_delete_view(LoginRequiredMixin, UserPassesTestMixin, DeleteView):
    model = ExamTemplates
    success_url = '/'

    # If authorized
    def test_func(self):
        exam_template = self.get_object()
        if self.request.user == exam_template.teacher:
            return True
        return False


