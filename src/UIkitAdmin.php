<?php

namespace Drupal\uikit_admin;

use Drupal\Core\Template\Attribute;

/**
 * Provides helper functions for the UIkit Admin theme.
 */
class UIkitAdmin {

  public static function getPageTemplateAttributes() {
    $page_attributes = [];

    // Set the page container attributes.
    $page_container_attributes = new Attribute;
    $page_container_attributes->setAttribute('id', 'page--content-wrapper');
    $page_container_attributes->addClass('uk-container');
    $page_container_attributes->addClass('uk-container-center');
    $page_container_attributes->addClass('uk-margin-bottom');
    $page_attributes['page_container_attributes'] = $page_container_attributes;

    // Set the content attributes.
    $content_attributes = new Attribute;
    $content_attributes->setAttribute('id', 'page--content');
    $content_attributes->addClass('uk-width-1-1');
    $page_attributes['content_attributes'] = $content_attributes;

    return $page_attributes;
  }

  public static function getViewsUIButtons() {
    return [
      'Add and configure @types',
      'Duplicate @display_title',
      'Delete @display_title',
      'Duplicate as @type',
      'Disable @display_title',
    ];
  }

  public static function getViewsUIDisplayButtons() {
    return [
      'Add @display',
    ];
  }

  public static function getViewsUILinks() {
    return [
      'class' => [
        'views-ui-settings-bucket-operations',
      ],
      'id' => [
        'views-display-extra-actions',
      ],
    ];
  }

  public static function getViewsUITabBuckets() {
    return[
      'views_ui_display_tab_bucket',
    ];
  }
}
