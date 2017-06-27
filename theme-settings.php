<?php

/**
 * @file
 * Provides theme settings for the UIkit Admin theme.
 */

use Drupal\Core\Extension\InfoParser;
use Drupal\uikit\UIkit;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function uikit_admin_form_system_theme_settings_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id = NULL) {
  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Inform the user theme settings have been disabled. No theme settings will
  // be used by UIkit Admin anyway, since we explicitly set attributes and
  // UIkit components in preprocess/process/theme/alter functions and Twig
  // templates.
  drupal_set_message(t('Theme settings for UIkit Admin have been disabled. Theme settings have no affect on UIkit Admin since attributes and UIkit components are explicitly set by the theme.'), 'warning');

  $uikit_elements = [
    'theme',
    'layout',
    'navigations',
    'uikit_details'
  ];

  // Remove each UIkit vertical tab so the settings cannot be changed.
  foreach ($form as $index => $item) {
    if (in_array($index, $uikit_elements)) {
      unset($form[$index]);
    }
  }

  unset($form['favicon']['favicon_preview']);
  unset($form['logo']['logo_preview']);

  // Open the logo and favicon details elements by default.
  $form['logo']['#open'] = TRUE;
  $form['favicon']['#open'] = TRUE;
}
