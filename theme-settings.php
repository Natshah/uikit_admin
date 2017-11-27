<?php

/**
 * @file
 * Provides theme settings for UIkit Admin theme.
 */

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

  // Get the active theme name.
  $build_info = $form_state->getBuildInfo();
  $active_theme = \Drupal::theme()->getActiveTheme();
  $theme = $active_theme->getName();
  $theme_key = $build_info['args'][0] === $theme ? $build_info['args'][0] : $theme;

  // Navigational settings.
  $form['navigations']['navbar'] = [
    '#type' => 'details',
    '#title' => t('Navbar'),
    '#description' => t('Configure settings for the navbar menu.'),
    '#attributes' => [
      'open' => 'open',
    ],
    '#weight' => -1,
  ];
  $form['navigations']['navbar']['sticky_navbar'] = [
    '#type' => 'checkbox',
    '#title' => t('Sticky navbar'),
    '#description' => t('Check this box to enable the sticky navbar.'),
    '#default_value' => UIkit::getThemeSetting('sticky_navbar', $theme_key),
  ];
}
