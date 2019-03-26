from django.db.models.signals import post_save
from django.contrib.auth.models import Group
from django.dispatch import receiver
from .models import PGUser

@receiver(post_save, sender=PGUser)
def add_user_to_students_group(sender, instance, created, **kwargs):
    """Post-create user signal that adds the user to everyone group."""
    if created:
        students_group = Group.objects.get(name='students')
        students_group.user_set.add(instance)
